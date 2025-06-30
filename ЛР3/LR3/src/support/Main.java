package support;

/**
 * Клас для демонстрації роботи системи.
 */
public class Main {
    public static void main(String[] args) {
        SupportCenter center = SupportCenter.getInstance(); // Singleton

        // Запит 1: простий
        SupportRequest req1 = new LogDecorator(
                new BasicRequest("Не працює мишка", Priority.LOW));
        center.processRequest(req1);

        // Запит 2: підвищений пріоритет
        SupportRequest req2 = new PriorityDecorator(
                new LogDecorator(
                        new BasicRequest("Проблеми з мережею", Priority.LOW)),
                Priority.MEDIUM);
        center.processRequest(req2);

        // Запит 3: критичний
        SupportRequest req3 = new LogDecorator(
                new PriorityDecorator(
                        new BasicRequest("Сервер недоступний", Priority.MEDIUM),
                        Priority.HIGH));
        center.processRequest(req3);
    }
}
