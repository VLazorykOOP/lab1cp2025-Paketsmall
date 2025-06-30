package support;

/**
 * Абстрактний клас, який реалізує шаблон Chain of Responsibility.
 * Кожен обробник намагається обробити запит або передає далі.
 */
public abstract class Handler {
    protected Handler next;

    // Встановлює наступного обробника в ланцюзі
    public void setNext(Handler next) {
        this.next = next;
    }

    // Метод обробки запиту
    public void handle(SupportRequest request) {
        if (!process(request) && next != null) {
            next.handle(request); // передати далі
        } else if (next == null) {
            System.out.println("⚠ Немає обробника для запиту: " + request.getDescription());
        }
    }

    // Метод, який перевизначають підкласи – чи можуть вони обробити запит
    protected abstract boolean process(SupportRequest request);
}
