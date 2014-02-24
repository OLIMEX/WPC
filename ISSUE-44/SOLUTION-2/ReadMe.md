This code reads an input file (ECGSample.txt) containing the EEG-SMT data and calculates the heartbeats from the data.  There are 6 channels of data in this input file, but initially we don't know which channel contains the ECG values.  This code makes an assumption that there's only 1 channel of data so as soon as it detects a channel with some viable ECG data in it, it only looks at that channel.  In the sample input file, the ECG data is actually held in channel 0.

The code calculates the heartbeats by:

1.  Parsing each packet of ECG data from the input file into an object and creates a list of them.  If there's a partial packet at the end of stream, we ignore it.
2.  The list of ECG packets isn't helpful so we create a new object that contains the data from each channel in an array.  I guess I could have generated this object straight away rather than parse into a list of packets first.
3.  We then scan through each channel looking for one that contains an ECG trace.  We look at how much the data values change from one sample to another.  If we detect a change that's greater than a defined "differential threshold", we use that channel's data and ignore all other channels.
4.  Then we calculate the heartbeats by measuring the time gap between any 2 consecutive samples where the differential movement is greater than the threshold.  Any heartbeat rate more than a maximum limit is rejected.
5.  The heartbeats found are listed on the console.  I also write out the channel values into a CSV file, 1 column per channel, which can be read into Excel or a database for subsequent analysis.

The sample data contains 3 heartbeats so the rates found by this code are:

75.67
77.97

Enjoy.

Nigel Mollett