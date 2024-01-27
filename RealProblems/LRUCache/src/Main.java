public class Main {
    public static void main(String[] args) {
        LruCache cache = new LruCache(3);
        cache.put(1, 123);
        cache.displayCache();
        cache.put(2, 234);
        cache.displayCache();
        cache.put(3, 345);
        cache.displayCache();
        System.out.println(cache.get(2));
        cache.displayCache();
        System.out.println(cache.get(4));
        cache.displayCache();
        cache.put(4, 456);
        cache.displayCache();
        cache.put(3, 333);
        cache.displayCache();
        cache.put(1, 111);
        cache.displayCache();
        System.out.println(cache.get(3));
        cache.displayCache();
        System.out.println(cache.get(4));
        cache.displayCache();
        cache.put(5,567);
        cache.displayCache();
    }
}