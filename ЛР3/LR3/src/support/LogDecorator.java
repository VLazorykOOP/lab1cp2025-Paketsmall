package support;

/**
 * Декоратор, який додає логування запиту при створенні.
 */
public class LogDecorator extends RequestDecorator {
    public LogDecorator(SupportRequest wrapped) {
        super(wrapped);
        logRequest();
    }

    // Метод логування
    private void logRequest() {
        System.out.println("[LOG] Отримано запит: " + wrapped.getDescription());
    }
}
