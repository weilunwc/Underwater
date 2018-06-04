# change the video title output from time stamp to date time 
import datetime
import glob
from shutil import move

if __name__=='__main__':
    video_list = [f for f in glob.glob("*.avi")]
    for video in video_list:
        char_array = list(video)
        processed = False
        for digit, s in enumerate(char_array):
            if s.isdigit() == False or digit > 9:
                if digit < 9:
                    processed = True
                index = digit
                break
        if processed:
            break
        timestamp = ''.join(char_array[:index])
        date_time = datetime.datetime.fromtimestamp(float(timestamp))
        date_time = date_time.strftime("%Y-%m-%d-%H-%M")
        move(video, date_time + '.avi') 

