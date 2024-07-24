package linkedlist;

public interface List<E> {
	public boolean isEmpty();
	public int size();
	public void addFirst(E anItem);
	public void addLast(E anItem);
	public E removeFirst();
	public E removeLast();
	public E getFirst();
	public E getLast();
	public E get(int index);

}
