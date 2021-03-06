def calculateAllAsmanyNumbers(asmanyNumbers):
    # for 2 and 3, 2 is the asmany number i.e. the number of asmany STRINGS 
    # of length 2 and 3 respectively.
    asmanyNumbers.add(2)
    prev = 2 # for n = 2
    for n in xrange(3, 3334): 
        # or we can loop till the asmanynumber is greater than 10^1000
        if n%2 == 0:
            # See the editorial http://discuss.codechef.com/questions/2097/lebinary-editorial
            # For even N, number of asmany strings of length N is 2* ((N-2) C (N/2)-1)
            # This is equal to 2 * previous asmany number. 
            prev = 2 * prev
        else:
            # for odd this is (2*(n/2)-1)*prev/(n/2)
            temp = n/2
            prev = (2*temp-1)*prev/temp
        asmanyNumbers.add(prev)

def main():
    T = int(raw_input())
    asmanyNumbers = set()
    calculateAllAsmanyNumbers(asmanyNumbers)
    for test in xrange(T):
        N = int(raw_input())
        if N in asmanyNumbers:
            print "YES"
        else:
            print "NO"

if __name__ == "__main__":
    main()
