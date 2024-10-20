import random
from datetime import datetime
cu = datetime.now()
with open("/dev/random", "rb") as f:
    cu = f.read(10)

x_max = 20
y_max = 10
z_max = 10
x_min = 0
y_min = -10
z_min = -10

r_max = 0.2
r_min = 0.01

n = int(input("#Enter number of objects: \n"))

obj_type = input("#Enter object type (sp, pl, tr): \n")
if obj_type == "sp":
    r_max = 0.8
    r_min = 0.3
elif obj_type == "pl":
    r_max = 0.2
    r_min = 0.01
elif obj_type == "tr":
    r_max = 0.8
    r_min = 0.3
else:
    print("Invalid object type")
    exit()

random.seed(cu)


def gen_sp():
    p_x = random.random() * (x_max - x_min) + x_min
    p_y = random.random() * (y_max - y_min) + y_min
    p_z = random.random() * (z_max - z_min) + z_min
    r = random.random() * (r_max - r_min) + r_min
    c_r = int(random.random() * 255)
    c_g = int(random.random() * 255)
    c_b = int(random.random() * 255)
    return "sp sq" + str(i) + "-" + str(random.random()) + " " + str(p_x) + "," + str(p_y) + "," + str(p_z) + " " + str(r) + " " + str(c_r) + "," + str(c_g) + "," + str(c_b) + "_1_1_1"

def gen_pl():
    p_x = random.random() * (x_max - x_min) + x_min
    p_y = random.random() * (y_max - y_min) + y_min
    p_z = random.random() * (z_max - z_min) + z_min
    n_x = random.random() * (x_max - x_min) + x_min
    n_y = random.random() * (y_max - y_min) + y_min
    n_z = random.random() * (z_max - z_min) + z_min
    c_r = int(random.random() * 255)
    c_g = int(random.random() * 255)
    c_b = int(random.random() * 255)
    return "pl pl" + str(i) + "-" + str(random.random()) + " " + str(p_x) + "," + str(p_y) + "," + str(p_z) + " " + str(n_x) + "," + str(n_y) + "," + str(n_z) + " " + str(c_r) + "," + str(c_g) + "," + str(c_b) + "_1_1_1"

def gen_tr():
    p1_x = random.random() * (x_max - x_min) + x_min
    p1_y = random.random() * (y_max - y_min) + y_min
    p1_z = random.random() * (z_max - z_min) + z_min

    p2_x = random.random() * (r_max - r_min) + r_min + p1_x
    p2_y = random.random() * (r_max - r_min) + r_min + p1_y
    p2_z = random.random() * (r_max - r_min) + r_min + p1_z
    
    p3_x = random.random() * (r_max - r_min) + r_min + p1_x
    p3_y = random.random() * (r_max - r_min) + r_min + p1_y
    p3_z = random.random() * (r_max - r_min) + r_min + p1_z
    c_r = int(random.random() * 255)
    c_g = int(random.random() * 255)
    c_b = int(random.random() * 255)
    return "tr tr" + str(i) + "-" + str(random.random()) + " " + str(p1_x) + "," + str(p1_y) + "," + str(p1_z) + " " + str(p2_x) + "," + str(p2_y) + "," + str(p2_z) + " " + str(p3_x) + "," + str(p3_y) + "," + str(p3_z) + " " + str(c_r) + "," + str(c_g) + "," + str(c_b) + "_1_1_1"

def gen_obj(obj_type):
    switcher = {
        "sp": gen_sp,
        "pl": gen_pl,
        "tr": gen_tr,
    }
    return switcher.get(obj_type, lambda: "Invalid object type")

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
    print(gen_obj(obj_type)())
