import java.util.concurrent.ThreadLocalRandom;
import java.util.Scanner;
import java.util.Date;

class ComputePi {
	public static void main(String[] args) {
		Scanner inScan = new Scanner(System.in);

		System.out.println("Enter number of threads:");
		String input = inScan.nextLine();
		int threadNum = Integer.parseInt(input);

		System.out.println("Enter number of throws:");
		input = inScan.nextLine();
		int throwNum = Integer.parseInt(input);

		Date startTime = new Date();
		long startTimeMS = startTime.getTime();

		HitCount dartData = new HitCount();

		CalcByDart[] threads = new CalcByDart[threadNum];

		for (int index = 0; index < threadNum; index++) {
			threads[index] = new CalcByDart(dartData, throwNum / threadNum);
			threads[index].start();
		}

		for (int index = 0; index < threadNum; index++) {
			try {
				threads[index].join();
			} catch (InterruptedException e) {}
		}

		double pi = ((double)dartData.hits / (double)dartData.totalThrows) * 4.0;
		System.out.println(dartData.hits);
		System.out.println(dartData.totalThrows);
		System.out.println(threadNum);
		System.out.println("pi = " + pi);

		Date finishTime = new Date();
		long finishTimeMS = finishTime.getTime();
		long executionTime = finishTimeMS - startTimeMS;
		System.out.println("Execution time was " + executionTime + " ms");
	}
}

class HitCount { //pass object to thread to pass pointer
	int hits;
	int totalThrows;
}

class CalcByDart extends Thread {
	int throwCount;
	HitCount dartThrows;

	public CalcByDart(HitCount darts, int shots) {
		dartThrows = darts;
		throwCount = shots;
	}

	public void run() {
		//throw darts
		int threadThrows = 0;
		int threadHits = 0;
		double x;
		double y;
		boolean isHit = false;
		for (int shot = 0; shot < throwCount; shot++) {
			x = ThreadLocalRandom.current().nextDouble(0,1); //weird execution times from Math.random() locking? smae for print?
			y = ThreadLocalRandom.current().nextDouble(0,1);
			isHit = Math.sqrt((Math.pow(x - .5, 2))+Math.pow(y - .5, 2)) < .5;

			threadThrows++;
			if (isHit) {
				threadHits++;
			}
		}
		//update dartThrows at the end, to avoid constant locking from slowing down the program
		//locking may be slower than the math
		synchronized(dartThrows) { //synchronized param is the object that owns the lock

			System.out.println("Thread throws = " + threadThrows + " Thread hits = " + threadHits);

			dartThrows.totalThrows = dartThrows.totalThrows + threadThrows;
			dartThrows.hits = dartThrows.hits + threadHits;
		}
		//System.out.println("Thread hits: " + dartThrows.hits); //locks
		//System.out.println("Thread throws: " + dartThrows.totalThrows);
	}
}

