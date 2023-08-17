from build import myLib as _spy
import numpy as np  


def test_resize():
    cv_obj = _spy.CVutils()
    image = cv_obj.read_image("flower.jpeg")
    print('org size: ', image.shape)
    resized_image = cv_obj.resize_image(image, 300, 300)
    print("resized", resized_image.shape)
    
    return True


def test_async_callbacks():
    # serves as state for async callback
    class Item:
        def __init__(self, value):
            self.value = value

    res = []

    # generate stateful lambda that will store result in `res`
    def gen_f():
        s = Item(3)
        return lambda j: res.append(s.value + j)

    # do some work async
    work = [1, 2, 3, 4]
    _spy.test_async_callback(gen_f(), work)
    # wait until work is done
    from time import sleep

    sleep(0.5)
    assert sum(res) == sum(x + 3 for x in work)

    return True

def test_lib():
    print(dir(_spy))

def test_callback():
    cv_obj = _spy.CVutils()
    out = cv_obj.read_with_callback("flower.jpeg", my_callback)
    print('after callback', out.shape)
    return True

def my_callback(image):
    cv_obj = _spy.CVutils()
    resized = cv_obj.resize_image(image, 100, 100)
    return resized

def test_numpy():
    cv_obj = _spy.CVutils()
    arr1 = np.array([1, 2])
    arr2 = np.array([5, 6])
    print(cv_obj.add_arrays(arr1, arr2))


def test_list():
    my_list = _spy.MyList()
    my_list.append(1)
    my_list.append(19)
    my_list.print()
    my_list.pop()
    my_list.print()

if __name__ == "__main__":
    test_lib()
    test_resize()
    test_callback()
    test_numpy()
    test_list()
    test_async_callbacks()




