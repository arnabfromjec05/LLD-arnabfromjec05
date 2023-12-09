package designPattern.builder;

public class Main {
    public static void main(String args[]) {
        HttpClient getClient = new HttpClient.HttpClientBuilder()
                .method("GET")
                .url("https://www.github.com")
                .headers("x-ms-auth: dsts")
                .body("{}")
                .build();

        HttpClient postClient = new HttpClient.HttpClientBuilder()
                .method("POST")
                .url("https://www.github.com")
                .headers("x-ms-auth: dsts")
                .body("{ prop1: abc }")
                .build();

        System.out.println(getClient);
        System.out.println(postClient);
    }
}
