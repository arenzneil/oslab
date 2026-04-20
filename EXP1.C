void sema_up (struct semaphore *sema) {
  enum intr_level old_level;
  old_level = intr_disable (); // Ensures atomicity
  if (!list_empty (&sema->waiters))
    thread_unblock (list_entry (list_pop_front (&sema->waiters),
                                struct thread, elem));
  sema->value++;
  intr_set_level (old_level);
}
