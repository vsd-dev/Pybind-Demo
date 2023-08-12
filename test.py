from build.myLib import CVutils, MyList
import numpy as np  
cv_obj = CVutils()
processed_image = cv_obj.process_image("flower.jpeg", 640, 480)
print("Resized: ", processed_image.shape)
arr1 = np.array([1, 2])
arr2 = np.array([5, 6])
print(cv_obj.add_arrays(arr1, arr2))


my_list = MyList()
my_list.append(1)
my_list.append(19)
my_list.print()
my_list.pop()
my_list.print()


