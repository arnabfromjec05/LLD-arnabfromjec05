import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class LruCache implements ICache{

    // actual cache storing the elements.
    private List<Element> cache;

    // stores indexes of elements present in cache.
    private Map<Integer, Element> cacheIndex;
    private int cacheCapacity;

    public LruCache(int size) {
        cache = new ArrayList<>();
        cacheIndex = new HashMap<>();
        cacheCapacity = size;
    }

    @Override
    public int get(int key) {
        if (cacheIndex.containsKey(key)) {
            // increase the priority of the fetched element
            Element element = cacheIndex.get(key);
            cache.remove(element);  // assume O(1) for doubly ll
            cache.addLast(element); // assume O(1) for doubly ll
            cacheIndex.put(key, element);

            // return the get result
            return element.getValue();
        }
        return -1;
    }

    @Override
    public void put(int key, int value) {
        if (cacheIndex.containsKey(key)) {
            Element element = cacheIndex.get(key);
            cache.remove(element);
            element.setValue(value);
            cache.addLast(element);
            cacheIndex.put(key, element);
        } else if (cache.size() < cacheCapacity) {
            Element element = new Element(key, value);
            cache.addLast(element);
            cacheIndex.put(key, element);
        } else {
            // cache is full, eviction to be done
            // Least recently used element will be evicted i.e. first in the list
            Element elementToBeRemoved = cache.removeFirst();
            cacheIndex.remove(elementToBeRemoved.getKey());
            Element elementToBeInserted = new Element(key, value);
            cache.addLast(elementToBeInserted);
            cacheIndex.put(key, elementToBeInserted);
        }
    }

    public void displayCache() {
        for (Element element: cache) {
            System.out.print("{" + element.getKey() + "," + element.getValue() + "} ");
        }
        System.out.println();
    }
}

class Element {
    private int key;
    private int value;

    public Element(int key, int value) {
        this.key = key;
        this.value = value;
    }

    public int getKey() {
        return key;
    }

    public void setKey(int key) {
        this.key = key;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }
}
