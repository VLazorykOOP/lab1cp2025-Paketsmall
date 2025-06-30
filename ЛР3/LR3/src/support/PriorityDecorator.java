package support;

/**
 * Декоратор, який змінює пріоритет запиту.
 */
public class PriorityDecorator extends RequestDecorator {
    private final Priority overriddenPriority;

    public PriorityDecorator(SupportRequest wrapped, Priority newPriority) {
        super(wrapped);
        this.overriddenPriority = newPriority;
    }

    @Override
    public Priority getPriority() {
        return overriddenPriority;
    }
}
