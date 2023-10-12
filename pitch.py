#!python3

LB=(
    ('A',),
    ('Ais', 'Bes',),
    ('B',),
    ('C',),
    ('Cis', 'Des',),
    ('D',),
    ('Dis', 'Ees',),
    ('E',),
    ('F',),
    ('Fis', 'Ges',),
    ('G',),
    ('Gis', 'Aes',),
)

PRESCALER = 1

def freq(n):
    return 440 * (2 ** (n/12))

def ocr(f):
    return (16*(10**6)/(f*PRESCALER)-1)

def main():

    assert len(LB) == 12

    print("#ifndef PITCH_TMP_H")
    print("#define PITCH_TMP_H")
    print()

    for n in range(0-12*4-9, 12*4+3):

        octave = (n+57)//12
        lbs = LB[(n+144)%12]
        print("//", round(freq(n)))
        for lb in lbs:
            print("#define PITCH_%s_%d %d" % (lb, octave, ocr(freq(n))))
        print()

        # print("%3d %d %-30s %s" % (n, octave, lbs, freq(n)))

    print("#endif")

if __name__ == "__main__":
    main()
