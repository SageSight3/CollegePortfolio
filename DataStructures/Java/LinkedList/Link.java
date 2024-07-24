package linkedlist;

//A link is a basic unit of a linked list that holds a string

public class Link {
	private Link next;
	private Link prev;
	private String item;

	public Link(String item) {
		this.item = item;
	}

	public String getItem() {
		return item;
	}

	public Link getNext() {
		return next;
	}

	public Link getPrev() {
		return prev;
	}

	public void setNext(Link next) {
		this.next = next;
	}

	public void setPrev(Link prev) {
		this.prev = prev;
	}

}
