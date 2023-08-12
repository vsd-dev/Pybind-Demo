from build.myLib import CVutils
import numpy as np
cv_obj = CVutils()
processed_image = cv_obj.process_image("flower.jpeg", 640, 480)
print("Resized: ", processed_image.shape)
arr1 = np.array([1, 2])
arr2 = np.array([5, 6])
print(cv_obj.add_arrays(arr1, arr2))

