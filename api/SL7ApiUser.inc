<?php

/**
 * @file
 *  SL7 User API
 *  
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

class SL7ApiUser {

  public static function generatePassword() {
    $chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
    $count = mb_strlen($chars);

    for ($i = 0, $result = ''; $i < 8; $i++) {
      $index = rand(0, $count - 1);
      $result .= mb_substr($chars, $index, 1);
    }

    return $result;
  }

  /**
   * Log in the site via e-mail.
   *
   * @param $mail
   *  E-mail address user.
   * @param $password
   *  Password user.
   * @return mixed
   *  Success - uid or bool FALSE.
   */
  public static function loginByMail($mail, $password) {
    if ($loading_user = user_load_by_mail($mail)) {
      require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
      if (user_check_password($password, $loading_user)) {
        global $user;
        $user = $loading_user;
        drupal_session_regenerate();
        return $loading_user->uid;
      }
      else {
        return FALSE;
      }
    }
    else {
      return FALSE;
    }
  }

  /**
   * Registration on the site via.
   *
   * @param $mail
   *  E-mail address user.
   * @param $pass
   *  Password.
   * @param bool|TRUE $send
   *  Send e-mail message after registration?
   * @param bool|TRUE $login
   *  Enter the site at user after login?
   * @param array $roles
   *  Add roles for new user.
   * @return mixed
   *  Success - uid or bool FALSE.
   */
  public static function regByMail($mail, $pass, $send = TRUE, $login = TRUE, $roles = array()) {
    if (!valid_email_address($mail)) {
      drupal_set_message(t('Invalid e-mail address format.'), 'error');
      return FALSE;
    }

    $match_mail = db_select('users', 'u')
      ->condition('mail', $mail)
      ->countQuery()
      ->execute()
      ->fetchField();

    if (isset($match_mail) && $match_mail > 0) {
    	drupal_set_message(t("This e-mail already exists. Use the <a href='/user/password?name=@mail'>password recovery form</a>. Or enter another e-mail.", array('@mail' => $mail)), 'error');
      return FALSE;
    }

    $mail = preg_replace("/[^\x20-\xFF]/","",@strval($mail));

    if (strlen($mail) == 0)
      return FALSE;

    $parts = explode("@", $mail);
    $name = $parts[0];

    $i = 0;
    do {
      $count = db_select('users')
        ->condition('name', $name)
        ->countQuery()
        ->execute()
        ->fetchField();

      if ($count != 0) {
        $i++;
        $name = $name . $i;
      }
    } while ($count != 0);

    $new_user = array(
      'name' => $name,
      'mail' => $mail,
      'pass' => $pass,
      'status' => 1,
      'init' => $mail,
      'roles' => array(
        DRUPAL_AUTHENTICATED_RID => 'authenticated user',
      ),
    );

    if (!empty($roles)) {
      foreach ($roles as $role) {
        $rid = user_role_load_by_name($role)->rid;
        $new_user['roles'][$rid] = $role;
      }
    }

    $save_user = user_save('', $new_user);
    $save_user->password = $pass;

    if ($login) {
      global $user;
      $user = $save_user;
      drupal_session_regenerate();
    }

    if ($send) {
      drupal_mail('user', 'register_no_approval_required', $mail, NULL, array('account' => $user), variable_get('site_mail'));
    }

    return $save_user->uid;
  }
}