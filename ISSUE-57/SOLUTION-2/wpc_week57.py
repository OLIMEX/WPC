#!/usr/bin/env python
# 13.Jun.2014
# Nikolay Dimitrov

import sys, urllib2

HTML_OPEN_TAG  = "<"
HTML_CLOSE_TAG = ">"

STATE_IDLE = 0
STATE_TAG  = 1
STATE_TEXT = 2

def main(args):
    print "Weekend Programming Challenge, Week 57"
    print "Solution written by Nikolay Dimitrov\n"

    if len(args) < 2:
        print "Usage: python %s <url>" % args[0]
        return 1

    url = args[1]
    print "Reading URL: %s" % url
    s = urllib2.urlopen(url).read()

    state = STATE_IDLE
    tag_chars = 0
    text_chars = 0

    for line in s.splitlines():

        for c in line:
            if state == STATE_IDLE:
                if c == HTML_OPEN_TAG:
                    next_state = STATE_TAG
                    tag_chars += 1
                else:
                    next_state = STATE_TEXT
                    text_chars += 1

            elif state == STATE_TAG:
                if c == HTML_CLOSE_TAG:
                    next_state = STATE_TEXT
                tag_chars += 1

            elif state == STATE_TEXT:
                if c == HTML_OPEN_TAG:
                    next_state = STATE_TAG
                    tag_chars += 1
                else:
                    text_chars += 1
            
            else:
                raise ValueError("ERROR: Invalid state: %d!" % state)

            state = next_state

    print "Text/HTML ratio: %.3f" % (float(text_chars) / tag_chars)

if __name__ == "__main__":
    main(sys.argv)
