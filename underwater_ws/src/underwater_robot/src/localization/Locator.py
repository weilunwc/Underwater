#!/usr/bin/env python
# Code modified from Blue Robotics
# https://github.com/waterlinked/examples 
# Use the Sonar system to Collect x,y data

from __future__ import print_function

import sys
import requests
import argparse
import json
import time

def get_data(url):
    # communicate with server
    try:
        r = requests.get(url)
    except requests.exceptions.RequestException as exc:
        print("Exception occured {}".format(exc))
        return None

    if r.status_code != requests.codes.ok:
        print("Got error {}: {}".format(r.status_code, r.text))
        return None

    return r.json()


class Locator:
    # Communicate with the Blue Robotics locator server for location info 
    def __init__(self, baseurl='http://192.168.2.94', external_depth=False):
        # The locator default only gets x,y value
        # Can set external depth for fusion
        self.baseurl = baseurl
        self.external_depth = external_depth
        self.delay_time = 1
        
        
        
    def set_depth(self, depth, temp):
        # Send depth and temp info to the locator server for sensor fusion
        # depth: positive value (m)
        # temp: Celcius 
        
        # Make sure depth is positive
        depth = abs(depth)
        if depth > 100:
            depth = 100
        if temp < -10:
            temp = -10
        url = '{}/api/v1/external/depth'.format(self.baseurl)

        payload = dict(depth=depth, temp=temp)
        r = requests.put(url, json=payload, timeout=10)

        if r.status_code != 200:
            print("Error setting depth: {} {}".format(r.status_code, r.text))

    def get_acoustic_position(self):
        # get local coordinates from acoustic locator
        # return x,y,z TODO check units and format
        data = get_data("{}/api/v1/position/acoustic/filtered".format(self.baseurl))
        if data:
            if self.external_depth:
                x = data["x"]
                y = data["y"]
                # Since this is depth, we want it negative
                z = -data["z"]
                return x, y, z
            else:
                x = data["x"]
                y = data["y"]
                return x, y
    
    def get_global_position(self):
        # get latitude and longitude from GPS 
        # Note: we don't have this module for now
        data = get_data("{}/api/v1/position/global".format(self.url))
        latitude = data['lat']
        longitude = data['lon']
        return latitude, longitude


