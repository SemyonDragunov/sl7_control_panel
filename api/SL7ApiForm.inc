<?php

/**
 * @file
 *  Form API.
 */

class SL7ApiForm {

  /**
   * Return rendered form.
   *
   * @param string $form_id Form id
   * @return string
   */
  public static function getRenderForm($form_id) {
    $form_state = array();
    $args = func_get_args();
    // Remove $form_id from the arguments.
    array_shift($args);
    $form_state['build_info']['args'] = $args;
    $form =  drupal_build_form($form_id, $form_state);

    return drupal_render($form);
  }

  /**
   * Set form placeholder.
   * @param array $element Form element array
   * @param string|NULL $placeholder Placeholder value
   * @param boolean $hide_title Set TRUE if you want hide title
   */
  public static function setPlaceholder(&$element, $placeholder = NULL, $title_display = 'invisible') {
    if (!$placeholder) {
      $placeholder = $element['#title'];
    }
    $element['#attributes']['placeholder'] = $placeholder;

    if ($title_display) {
      $element['#title_display'] = $title_display;
    }
  }

  /**
   * Remove system hidden values from GET form.
   *
   * @param array $form Form array
   * @return array
   */
  public static function prepareGetForm(array $form) {
    unset($form['form_token']);
    unset($form['form_build_id']);
    unset($form['form_id']);
    unset($form['submit']['#name']);

    return $form;
  }

  /**
   * Get clear system values from form values.
   *
   * @param array $form_state form_state array
   * @return mixed
   */
  public static function clearValuesForm(array $form_state) {
    unset($form_state['values']['form_token']);
    unset($form_state['values']['form_build_id']);
    unset($form_state['values']['form_id']);
    unset($form_state['values']['op']);
    unset($form_state['values']['actions']);

    return $form_state['values'];
  }

  /**
   * Recursive remove required flag.
   *
   * @param array $form Form array
   */
  public static function removeRequired(&$form) {
    if (!empty($form['#required'])) {
      $form['#required'] = FALSE;
    }
    foreach (element_children($form) as $key) {
      if (is_array($form[$key])) {
        self::removeRequired($form[$key]);
      }
    }
  }
}