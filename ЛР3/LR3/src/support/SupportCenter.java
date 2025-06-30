package support;

/**
 * Singleton – єдина точка доступу до ланцюга обробників.
 */
public class SupportCenter {
    private static SupportCenter instance; // єдиний екземпляр
    private final Handler handlerChain;    // ланцюг обробників

    private SupportCenter() {
        // Створюємо об'єкти обробників
        Handler first = new FirstLevelSupport();
        Handler second = new SecondLevelSupport();
        Handler expert = new ExpertSupport();

        // Формуємо ланцюг
        first.setNext(second);
        second.setNext(expert);

        handlerChain = first;
    }

    // Метод доступу до єдиного екземпляра
    public static SupportCenter getInstance() {
        if (instance == null) {
            instance = new SupportCenter();
        }
        return instance;
    }

    // Метод для обробки запиту
    public void processRequest(SupportRequest request) {
        handlerChain.handle(request);
    }
}
