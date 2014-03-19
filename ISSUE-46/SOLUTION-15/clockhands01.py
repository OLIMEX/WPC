
# angular speed of hour arrow = 360degrees/12hours = 0.5degrees/minute
# angular speed of minute arrow = 360degrees/60minutes = 6degrees/minute
# degree of hour arrow at m minute = 0.5m + h ;h = starting degree of hour arrow, 30 degrees/hour
# degree of minute arrow at m minute = 6m
# equation when both arrows across 
# 0.5m + h = 6m
# h = 5.5m
# m = h/5.5

for h in range(12):
    print "hour=", h, "minute=", ((h*30.0) / 5.5) % 60