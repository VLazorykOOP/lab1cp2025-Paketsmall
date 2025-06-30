package support;

/**
 * Інтерфейс для запитів технічної підтримки.
 * Усі запити повинні повертати опис і рівень пріоритету.
 */
public interface SupportRequest {
    String getDescription();   // Опис проблеми
    Priority getPriority();    // Пріоритет запиту
}
