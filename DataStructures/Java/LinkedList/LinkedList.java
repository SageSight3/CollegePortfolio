package linkedlist;

/*A linked list is a list of strings stored in links
*that can be added to, removed from, or called to return the string of
*a specific link
*/

public class LinkedList {
	private Link firstLink;
	private Link lastLink;

	public LinkedList() {
	}

	public int size() {
		int count = 0;
		Link aLink = firstLink;
		while (aLink != null) {
			++count;
			aLink = aLink.getNext();
		}
		return count;
	}

	public String get(int index) {
		Link aLink = firstLink;
		if (isEmpty()) {
			return null;
		}
		for (int count = 0; count < index; ++count) {
			aLink = aLink.getNext();
		}
		return aLink.getItem();
	}

	public boolean isEmpty() {
		return firstLink == null;
	}

	public void addFirst(String anItem) {
		Link aLink = new Link(anItem);
		if (isEmpty()) {
			lastLink = aLink;
		} else {
			aLink.setNext(firstLink);
			firstLink.setPrev(aLink);
		}
		firstLink = aLink;
	}

	public void addLast(String anItem) {
		Link aLink = new Link(anItem);
		if (isEmpty()) {
			firstLink = aLink;
		} else {
			aLink.setPrev(lastLink);
			lastLink.setNext(aLink);
		}
		lastLink = aLink;
	}

	public String removeFirst() {
		if (isEmpty()) {
			return null;
		}
		String returnItem = firstLink.getItem();
		firstLink = firstLink.getNext();
		if (firstLink != null) {
			firstLink.setPrev(null);
		} else {
			lastLink = null;
		}
		return returnItem;
	}

	public String removeLast() {
		if (isEmpty()) {
			return null;
		}
		String returnItem = lastLink.getItem();
		lastLink = lastLink.getPrev();
		if (lastLink != null) {
			lastLink.setNext(null);
		} else {
			firstLink = null;
		}
		return returnItem;
	}

	public String getFirst() {
		if (isEmpty()) {
			return null;
		}
		return firstLink.getItem();
	}

	public String getLast() {
		if (isEmpty()) {
			return null;
		}
		return lastLink.getItem();
	}
}
