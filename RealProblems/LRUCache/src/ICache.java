public interface ICache {
    /**
     * Gets an element from the cache
     * @return element
     */
    int get(int key);

    /**
     * Puts an element into the cache
     */
    void put(int key, int value);

}
