package support;

/**
 * Обробляє запити середнього пріоритету.
 */
public class SecondLevelSupport extends Handler {
    @Override
    protected boolean process(SupportRequest request) {
        if (request.getPriority() == Priority.MEDIUM) {
            System.out.println("✅ Другий рівень обробив: " + request.getDescription());
            return true;
        }
        return false;
    }
}
