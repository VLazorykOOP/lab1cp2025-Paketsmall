package support;

/**
 * Базова реалізація інтерфейсу SupportRequest.
 * Містить лише опис і пріоритет.
 */
public class BasicRequest implements SupportRequest {
    private final String description;
    private final Priority priority;

    public BasicRequest(String description, Priority priority) {
        this.description = description;
        this.priority = priority;
    }

    @Override
    public String getDescription() {
        return description;
    }

    @Override
    public Priority getPriority() {
        return priority;
    }
}
