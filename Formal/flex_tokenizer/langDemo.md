# Anabolic Steroid Nyelv grammatika

## 2 alaptipus (egesz es valos)

```
    int     int_number
    double  real_number
    text    string_value

    int     int_number = 100
    double  double_number = 99.99
    text    string_value = 'Hello World!'
```

## Aritmetikai Muveletek

```
    int a = 1
    int b = 2
    int c = a + b
    int c = a - b
    int c = a * b
    int c = a / b
    int c = a % b
    int c = a * (a + b)
```

## Kiiras Beolvasas

```
    int hight = get()
    hight = get('Enter a random integer!')

    log('This is a text. The Mount Everest is ${hight}m high.')
    log(high)
```

## if - then - else | while

```
    int i = 1
    till(i != 10) {
        i = i + 1

        test(i == 5) {
            log('${i}th cycle!')
        } instead test(i == 6) {
            log('${i}${i}${i}')
        } instead {
            log{'idk'}
        }
    }

    test( i == 5 and i != 6 or i != 7) {
        log('shit')
    }

```

## arrays and typeconversion

```
    int a = []
    int a = [1,2,3]
```
