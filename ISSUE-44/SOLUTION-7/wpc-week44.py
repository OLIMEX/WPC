#!/usr/bin/env python
# encoding: utf-8
# http://olimex.wordpress.com/2014/02/21/weekend-prorgamming-challenge-week-44-ecg-heart-beat-detection/
# Matthias Schmitz <matthias@sigxcpu.org>


import argparse
try:
    # if matplotlib is installed show a graph
    import matplotlib.pyplot as plt
except:
    print "Could not import matplotlib.pyplot"
    plt = None


def read_data_from_file(inputfile):
    # read the data and slice out the six data channels
    with open(inputfile, 'rb') as ecp_input:
        dataset = 'dummy'
        samples = []
        while dataset:
            dataset = ecp_input.read(34)
            if len(dataset) == 34:
                # a list with all the data, one tuple per 1/256 second (256Hz)
                samples.append((int(dataset[8:12], 16),
                               int(dataset[12:16], 16),
                               int(dataset[16:20], 16),
                               int(dataset[20:24], 16),
                               int(dataset[24:28], 16),
                               int(dataset[28:32], 16)))
    return samples


def graph_samples(data):
    # no idea how to read the data so lets graph them
    # Ok, channel zero looks like a ecg :)
    plt.plot(range(len(data)), data)
    plt.xlabel('time in 1/256 s (3.90625 milliseconds )')
    plt.autoscale(enable=True)
    plt.show()


def count_heartbeats(data, channel):
    '''
    from looking at the graph and reading wikipedia
    (http://en.wikipedia.org/wiki/QRS_complex) i guess a heartbeat can be
    detected by the slope of the curve in the QRS complex (high y-value
    followed by negative y-value).
    m = (y2 - y1) / (x2 - x1)
    '''
    heartbeats = 0
    m = 0
    y1 = None
    for tup in data:
        y2 = tup[channel]
        if y1:
            m = y2 - y1  # x2 - x1 is always 1
            # if the slope < -400 it should be a heart beat
            if m < -400:
                heartbeats += 1
        y1 = y2

    return heartbeats


def calculate_heartbeats_per_minute(data, channel):
    # calculate heartbeats per minute
    heartbeats = count_heartbeats(data, channel)
    seconds = len(data) / 256.0
    print 'The data has %s heartbeats in %s seconds' % (heartbeats, seconds)
    return round(heartbeats / seconds * 60)


def main():

    parser = argparse.ArgumentParser()
    parser.add_argument('--input-file', dest='inputfile', required=True,
                        help='file with ecg samples')
    args = parser.parse_args()

    samples = read_data_from_file(args.inputfile)
    hb = calculate_heartbeats_per_minute(data=samples, channel=0)
    print "The heartrate is %s beats per minute." % hb

    if plt:
        graph_samples(samples)


if __name__ == '__main__':
    main()
