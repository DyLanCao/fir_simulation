from numpy import sin, arange, pi
from scipy.signal import lfilter, firwin
from pylab import figure, plot, grid, show
import matplotlib.pyplot as plt 
import numpy as np

#------------------------------------------------
# Create a signal for demonstration.
#------------------------------------------------
# 320 samples of (1000Hz + 15000 Hz) at 48 kHz
sample_rate = 48000.
nsamples = 320

F_1KHz = 300.
A_1KHz = 1.0

F_15KHz = 23000
A_15KHz = 0.8

t = arange(nsamples) / sample_rate
signal = A_1KHz * sin(2*pi*F_1KHz*t) + A_15KHz*sin(2*pi*F_15KHz*t)

n = len(signal)
k = np.arange(n)
T = n/sample_rate
frq = k/T
#------------------------------------------------
# Create a FIR filter and apply it to signal.
#------------------------------------------------
# The Nyquist rate of the signal.
nyq_rate = sample_rate / 2.

# The cutoff frequency of the filter: 6KHz
cutoff_hz = 300.0

# Length of the filter (number of coefficients, i.e. the filter order + 1)
numtaps = 29

# Use firwin to create a lowpass FIR filter
#fir_coeff = firwin(numtaps, cutoff_hz/nyq_rate)

## high pass filter
fir_coeff = firwin(numtaps, cutoff_hz/nyq_rate, window = "hanning", pass_zero=False)

# Use lfilter to filter the signal with the FIR filter
filtered_signal = lfilter(fir_coeff, 1.0, signal)

#------------------------------------------------
# Plot the original and filtered signals.
#------------------------------------------------

# The first N-1 samples are "corrupted" by the initial conditions
warmup = numtaps - 1

# The phase delay of the filtered signal
delay = (warmup / 2) / sample_rate

YY = np.fft.fft(signal) 
YZ = np.fft.fft(filtered_signal) 

fig, ax = plt.subplots(4, 1)

ax[0].plot(t,signal)
ax[0].set_xlabel('Time')
ax[0].set_ylabel('Amplitude')

ax[1].plot(frq,abs(YY),'r') # plotting the spectrum
ax[1].set_xlabel('Freq (Hz)')
ax[1].set_ylabel('|Y(freq)|')

ax[2].plot(t,filtered_signal)
ax[2].set_xlabel('Time')
ax[2].set_ylabel('Amplitude')

ax[3].plot(frq,abs(YZ),'r') # plotting the spectrum
ax[3].set_xlabel('Freq (Hz)')
ax[3].set_ylabel('|Y(freq)|')

plt.show()
#------------------------------------------------
# Print values
#------------------------------------------------
def print_values(label, values):
    var = "float32_t %s[%d]" % (label, len(values))
    print "%-30s = {%s}" % (var, ', '.join(["%+.10f" % x for x in values]))
#print_values('signal', signal)
print_values('test_lowpass', fir_coeff)
#print_values('filtered_signal', filtered_signal)
