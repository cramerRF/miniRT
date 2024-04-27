import random
from datetime import datetime
cu = datetime.now()

x_max = 20
y_max = 10
z_max = 10
x_min = 0
y_min = -10
z_min = -10

r_max = 0.2
r_min = 0.01

n = 1000

random.seed(cu)

i = 0
while i < n:
    i += 1
    p_x = random.random() * (x_max - x_min) + x_min
    p_y = random.random() * (y_max - y_min) + y_min
    p_z = random.random() * (z_max - z_min) + z_min
    r = random.random() * (r_max - r_min) + r_min
    c_r = int(random.random() * 255)
    c_g = int(random.random() * 255)
    c_b = int(random.random() * 255)
    print("sp " + str(i) + " " 
            + str(p_x) + "," 
            + str(p_y) + "," 
            + str(p_z) + " " 
            + str(r) + " " 
            + str(c_r) + "," 
            + str(c_g) + "," 
            + str(c_b) + "_1_1_1" )
