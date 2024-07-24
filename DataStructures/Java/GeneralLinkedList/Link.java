package linkedlist;

//A link is a basic unit of a linked list that holds a string

public class Link<E> {
	private Link<E> next;
	private Link<E> prev;
	private E item;

	public Link(E item) {
		this.item = item;
	}

	public E getItem() {
		return item;
	}

	public Link<E> getNext() {
		return next;
	}

	public Link<E> getPrev() {
		return prev;
	}

	public void setNext(Link<E> next) {
		this.next = next;
	}

	public void setPrev(Link<E> prev) {
		this.prev = prev;
	}

}
