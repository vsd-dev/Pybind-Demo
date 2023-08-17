from build.myLib import CVutils, MyList
import numpy as np  
cv_obj = CVutils()
# processed_image = cv_obj.process_image("flower.jpeg", 300, 300)

image = cv_obj.read_image("flower.jpeg")
# def my_callback(array1, array2):
#     arr1 = np.array([1, 2])
#     arr2 = np.array([5, 6])
#     print(cv_obj.add_arrays(array1, array2))
#     print(f"Callback called")

# processed_image = cv_obj.process_image_with_cb("flower.jpeg", 640, 480, my_callback)
print("image: ", image.shape)

resized_image = cv_obj.resize_image(image, 300, 300)


print("resized", resized_image.shape)
arr1 = np.array([1, 2])
arr2 = np.array([5, 6])
print(cv_obj.add_arrays(arr1, arr2))


my_list = MyList()
my_list.append(1)
my_list.append(19)
my_list.print()
my_list.pop()
my_list.print()


