package support;

/**
 * Обробляє лише запити з низьким пріоритетом.
 */
public class FirstLevelSupport extends Handler {
    @Override
    protected boolean process(SupportRequest request) {
        if (request.getPriority() == Priority.LOW) {
            System.out.println("✅ Перший рівень обробив: " + request.getDescription());
            return true;
        }
        return false;
    }
}
