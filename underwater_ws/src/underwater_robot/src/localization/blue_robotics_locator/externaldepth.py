from __future__ import print_function
import requests
import argparse
import time
import logging

log = logging.getLogger()
logging.basicConfig(format='%(asctime)s %(message)s', level=logging.INFO)


def set_depth(url, depth, temp):
    payload = dict(depth=depth, temp=temp)
    r = requests.put(url, json=payload, timeout=10)
    if r.status_code != 200:
        log.error("Error setting depth: {} {}".format(r.status_code, r.text))


def main():
    parser = argparse.ArgumentParser(description="Push depth to Underwater GPS")
    parser.add_argument('-u', '--url', help='Base URL to use', type=str, default='http://demo.waterlinked.com')
    parser.add_argument('-d', '--depth', help='Depth to send', type=float, default=0.5)
    parser.add_argument('-t', '--temp', help='Temperature to send', type=float, default=10)
    parser.add_argument('-r', '--repeat', help='Repeat sending with a delay of the given number of seconds', type=int, default=5)

    args = parser.parse_args()
    args.depth = 10
    baseurl = args.url
    
    baseurl = 'http://192.168.2.94'
    log.info("Using baseurl: %s depth: %f temperature %f", args.url, args.depth, args.temp)
    
    delay_time = 0.5
    while True:
        log.info('Sending depth')
        set_depth('{}/api/v1/external/depth'.format(baseurl), args.depth, args.temp)

        if args.repeat < 1:
            break
        args.depth -= 0.05
        print("wating", delay_time)
        time.sleep(delay_time)


if __name__ == "__main__":
    main()
