package support;

/**
 * Обробляє критичні запити з високим пріоритетом.
 */
public class ExpertSupport extends Handler {
    @Override
    protected boolean process(SupportRequest request) {
        if (request.getPriority() == Priority.HIGH) {
            System.out.println("✅ Експерт обробив: " + request.getDescription());
            return true;
        }
        return false;
    }
}
