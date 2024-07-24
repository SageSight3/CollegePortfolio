//********************************
//****DO NOT MODIFY THIS FILE:****
//********************************

import java.util.*;

/**
 * ConsoleIO is a utility class used for reading input from and writing output to
 * the console, providing a basic way to communicate with the user in a text mode application.
 */
public class ConsoleIO {
	private static final Scanner in = new Scanner(System.in);

	private ConsoleIO() {
	}

	/**
	 * Prints a blank line to the console.
	 */
	public static void printLine() {
		System.out.println();
	}

	/**
	 * Prints the given String to the console, without a trailing newline character.
	 * @param s the String to print out.
	 */
	public static void print(String s) {
		System.out.print(s);
	}

	/**
	 * Prints the given Object to the console, without a trailing newline character.
	 * @param s the Object to print out.
	 */
	public static void print(Object s) {
		System.out.print(s);
	}

	/**
	 * Prints the given byte to the console, without a trailing newline character.
	 * @param s the byte to print out.
	 */
	public static void print(byte s) {
		System.out.print(s);
	}

	/**
	 * Prints the given short to the console, without a trailing newline character.
	 * @param s the short to print out.
	 */
	public static void print(short s) {
		System.out.print(s);
	}

	/**
	 * Prints the given int to the console, without a trailing newline character.
	 * @param s the int to print out.
	 */
	public static void print(int s) {
		System.out.print(s);
	}

	/**
	 * Prints the given long to the console, without a trailing newline character.
	 * @param s the long to print out.
	 */
	public static void print(long s) {
		System.out.print(s);
	}

	/**
	 * Prints the given float to the console, without a trailing newline character.
	 * @param s the float to print out.
	 */
	public static void print(float s) {
		System.out.print(s);
	}

	/**
	 * Prints the given double to the console, without a trailing newline character.
	 * @param s the double to print out.
	 */
	public static void print(double s) {
		System.out.print(s);
	}

	/**
	 * Prints the given boolean to the console, without a trailing newline character.
	 * @param s the boolean to print out.
	 */
	public static void print(boolean s) {
		System.out.print(s);
	}

	/**
	 * Prints the given char to the console, without a trailing newline character.
	 * @param s the char to print out.
	 */
	public static void print(char s) {
		System.out.print(s);
	}

	/**
	 * Prints the given String to the console, followed by a newline character.
	 * @param s the String to print out.
	 */
	public static void printLine(String s) {
		System.out.println(s);
	}

	/**
	 * Prints the given Object to the console, followed by a newline character.
	 * @param s the Object to print out.
	 */
	public static void printLine(Object s) {
		System.out.println(s);
	}

	/**
	 * Prints the given byte to the console, followed by a newline character.
	 * @param s the byte to print out.
	 */
	public static void printLine(byte s) {
		System.out.println(s);
	}

	/**
	 * Prints the given short to the console, followed by a newline character.
	 * @param s the short to print out.
	 */
	public static void printLine(short s) {
		System.out.println(s);
	}

	/**
	 * Prints the given int to the console, followed by a newline character.
	 * @param s the int to print out.
	 */
	public static void printLine(int s) {
		System.out.println(s);
	}

	/**
	 * Prints the given long to the console, followed by a newline character.
	 * @param s the long to print out.
	 */
	public static void printLine(long s) {
		System.out.println(s);
	}

	/**
	 * Prints the given float to the console, followed by a newline character.
	 * @param s the float to print out.
	 */
	public static void printLine(float s) {
		System.out.println(s);
	}

	/**
	 * Prints the given double to the console, followed by a newline character.
	 * @param s the double to print out.
	 */
	public static void printLine(double s) {
		System.out.println(s);
	}

	/**
	 * Prints the given boolean to the console, followed by a newline character.
	 * @param s the boolean to print out.
	 */
	public static void printLine(boolean s) {
		System.out.println(s);
	}

	/**
	 * Prints the given char to the console, followed by a newline character.
	 * @param s the char to print out.
	 */
	public static void printLine(char s) {
		System.out.println(s);
	}

	/**
	 * Reads an integer number from the console (in the range of -128 to 127), and returns it as a byte.
	 * @return the number entered in the console.
	 */
	public static byte readByte() {
		String s = in.nextLine();
		byte i = Byte.parseByte(s);
		return i;
	}

	/**
	 * Reads an integer number from the console (in the range of -32768 to 32767), and returns it as a short.
	 * @return the number entered in the console.
	 */
	public static short readShort() {
		String s = in.nextLine();
		short i = Short.parseShort(s);
		return i;
	}

	/**
	 * Reads an integer number from the console (in the range of -2147483648 to 2147483647), and returns it as an int.
	 * @return the number entered in the console.
	 */
	public static int readInt() {
		String s = in.nextLine();
		int i = Integer.parseInt(s);
		return i;
	}

	/**
	 * Reads an integer number from the console (in the range of -9223372036854775808 to 9223372036854775807), and returns it as a long.
	 * @return the number entered in the console.
	 */
	public static long readLong() {
		String s = in.nextLine();
		long i = Long.parseLong(s);
		return i;
	}

	/**
	 * Reads a decimal number from the console (in the range of roughly -10<sup>38</sup> to 10<sup>38</sup>), and returns it as a float.
	 * @return the number entered in the console.
	 */
	public static float readFloat() {
		String s = in.nextLine();
		float i = Float.parseFloat(s);
		return i;
	}

	/**
	 * Reads a decimal number from the console (in the range of roughly -10<sup>308</sup> to 10<sup>308</sup>), and returns it as a double.
	 * @return the number entered in the console.
	 */
	public static double readDouble() {
		String s = in.nextLine();
		double i = Double.parseDouble(s);
		return i;
	}

	/**
	 * Reads the value &quot;true&quot; or &quot;false&quot; from the console (without the quotes), and returns it as a boolean.
	 * @return the truth value entered in the console.
	 */
	public static boolean readBoolean() {
		String s = in.nextLine().trim();
		if (s.equals("true")) {
			return true;
		}
		else if (s.equals("false")) {
			return false;
		}
		else {
			throw new RuntimeException("Input String \"" + s + "\" is not \"true\" or \"false\"");
		}
	}

	/**
	 * Reads the next line of text from the console and returns it as a String.
	 * @return a line of text entered in the console.
	 */
	public static String readLine() {
		String s = in.nextLine();
		return s;
	}

}