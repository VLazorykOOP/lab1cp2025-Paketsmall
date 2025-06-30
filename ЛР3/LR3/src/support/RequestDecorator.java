package support;

/**
 * Абстрактний декоратор, який реалізує SupportRequest
 * і делегує виклики іншому об'єкту SupportRequest.
 */
public abstract class RequestDecorator implements SupportRequest {
    protected final SupportRequest wrapped; // Обгорнутий запит

    public RequestDecorator(SupportRequest wrapped) {
        this.wrapped = wrapped;
    }

    @Override
    public String getDescription() {
        return wrapped.getDescription();
    }

    @Override
    public Priority getPriority() {
        return wrapped.getPriority();
    }
}
