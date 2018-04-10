<section id="user-controls">
  <a class="icon-user" href="/user<?php print $uid = $GLOBALS['user']->uid != 0 ? '/' . $GLOBALS['user']->uid : ''; ?>"><?php t('My dashboard')?></a>
  <?php if ($GLOBALS['user']->uid != 0): ?>
    <a class="icon-logout" href="/user/logout"><?php t('Log out')?></a>
  <?php endif; ?>
</section>