import numpy

class LPfilter:
  def __init__(self, cutoff_freq, DT):
    self.cutoff_freq = cutoff_freq
    self.DT = DT
    self.last_input = numpy.array([])
    self.last_output = numpy.array([])
    self.output = numpy.array([])

  def update(self, value, cutoff_freq=None, DT=None):
    if cutoff_freq is not None and DT is not None:
      self.cutoff_freq = cutoff_freq
      self.DT = DT
    if self.last_input.shape[0] > 0:
      output = (self.cutoff_freq*self.DT*(self.last_input+value) - (self.cutoff_freq*self.DT-2)*self.last_output) / (self.cutoff_freq*self.DT+2)
    else:
      output = value
    self.last_input = value
    self.last_output = output
    self.output = output
    return output
