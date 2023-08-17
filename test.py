from build.myLib import CVutils, MyList
import numpy as np  
cv_obj = CVutils()

image = cv_obj.read_image("flower.jpeg")
print("image: ", image.shape)
resized_image = cv_obj.resize_image(image, 300, 300)
print("resized", resized_image.shape)

def my_callback(image):
    w = 300
    h = 300
    resized = cv_obj.resize_image(image, w, h)
    print("Inside callback")
    print("size: ", resized.shape)
    print("callback clled")
    return resized

cv_obj.read_with_callback("flower.jpeg", my_callback)


arr1 = np.array([1, 2])
arr2 = np.array([5, 6])
print(cv_obj.add_arrays(arr1, arr2))


my_list = MyList()
my_list.append(1)
my_list.append(19)
my_list.print()
my_list.pop()
my_list.print()


