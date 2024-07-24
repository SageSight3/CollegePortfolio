package linkedlist;

/*A linked list is a list of items stored in links
*that can be added to, removed from, or called to return the string of
*a specific link
*/

public class LinkedList<E> implements List<E> {
	private Link<E> firstLink;
	private Link<E> lastLink;

	public LinkedList() {
	}

	public int size() {
		int count = 0;
		Link<E> aLink = firstLink;
		while (aLink != null) {
			++count;
			aLink = aLink.getNext();
		}
		return count;
	}

	public E get(int index) {
		Link<E> aLink = firstLink;
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

	public void addFirst(E anItem) {
		Link<E> aLink = new Link<E>(anItem);
		if (isEmpty()) {
			lastLink = aLink;
		} else {
			aLink.setNext(firstLink);
			firstLink.setPrev(aLink);
		}
		firstLink = aLink;
	}

	public void addLast(E anItem) {
		Link<E> aLink = new Link<E>(anItem);
		if (isEmpty()) {
			firstLink = aLink;
		} else {
			aLink.setPrev(lastLink);
			lastLink.setNext(aLink);
		}
		lastLink = aLink;
	}

	public E removeFirst() {
		if (isEmpty()) {
			return null;
		}
		E returnItem = firstLink.getItem();
		firstLink = firstLink.getNext();
		if (firstLink != null) {
			firstLink.setPrev(null);
		} else {
			lastLink = null;
		}
		return returnItem;
	}

	public E removeLast() {
		if (isEmpty()) {
			return null;
		}
		E returnItem = lastLink.getItem();
		lastLink = lastLink.getPrev();
		if (lastLink != null) {
			lastLink.setNext(null);
		} else {
			firstLink = null;
		}
		return returnItem;
	}

	public E getFirst() {
		if (isEmpty()) {
			return null;
		}
		return firstLink.getItem();
	}

	public E getLast() {
		if (isEmpty()) {
			return null;
		}
		return lastLink.getItem();
	}
}
