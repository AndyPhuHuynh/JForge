class Jumps {
    private static void ifTest(int x) {
        if (x > 10) {
            System.out.println("Greater than 10!");
        } else if (x > 5) {
            System.out.println("Between 5 and 10!");
        } else {
            System.out.println("Less than 5!");
        }
    }

    private static void forTest(int numIters) {
        for (int i = 0; i < numIters; i++) {
            System.out.println(i);
        }
    }

    public static void main(String[] args) {
        ifTest(2);
        forTest(10);
    }
}