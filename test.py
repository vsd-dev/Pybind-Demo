from build.myLib import CVutils 
cv_obj = CVutils("sample.png")
resized_image = cv_obj.resize(640, 480)
print("Resized: ", resized_image.shape)
breakpoint()




