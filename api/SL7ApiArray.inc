<?php

/**
 * @file
 *  Array API.
 */

class SL7ApiArray {

  /**
   * Remove empty elements from array.
   *
   * @param array $array Source array
   * @return array
   */
  public static function removeEmptyElements($array) {
    return array_diff($array, array(''));
  }

  /**
   * Recursively convert an object to an array.
   *
   * @param $obj
   * @return array
   */
  public static function objectToArray($obj) {
    if(is_object($obj)) $obj = (array) $obj;
    if(is_array($obj)) {
      $new = array();
      foreach($obj as $key => $val) {
        $new[$key] = self::objectToArray($val);
      }
    }
    else $new = $obj;

    return $new;
  }

  /**
   * Insert element before/after key.
   *
   * @param array $array Input array
   * @param integer|string $key Array key
   * @param array $value Element
   * @param string $insert_type Insertion type 'before' or 'after'
   * @return array
   */
  public static function insert($array, $key, $value, $insert_type) {
    $key_position = array_search($key, array_keys($array), TRUE);

    if ($key_position !== FALSE) {
      $offset = ($insert_type == 'after') ? 1 : 0;
      $array = array_merge(
        array_slice($array, 0, $key_position + $offset, TRUE),
        $value,
        array_slice($array, $key_position + $offset, count($array), TRUE)
      );
    }
    else {
      $array = array_merge($array, $value);
    }

    return $array;
  }

  /**
   * Insert element before key.
   *
   * @param array $array Input array
   * @param integer|string $key Array key
   * @param array $value Element
   * @return array
   */
  public static function insertBefore($array, $key, $value) {
    return self::insert($array, $key, $value, 'before');
  }

  /**
   * Insert element after key.
   *
   * @param array $array Input array
   * @param integer|string $key Array key
   * @param array $value Element
   * @return array
   */
  public static function insertAfter($array, $key, $value) {
    return self::insert($array, $key, $value, 'after');
  }

  /**
   * Replace key name.
   *
   * @param array $array Input array
   * @param mixed $old_key Old key name
   * @param mixed $new_key New key name
   * @return array
   */
  public static function replaceKey($array, $old_key, $new_key) {
    if (isset($array[$old_key])) {
      $array = self::insertAfter($array, $old_key, array($new_key => $array[$old_key]));
      unset($array[$old_key]);
    }
    return $array;
  }

  /**
   * Remove elements from array by keys.
   *
   * @param array $array Input array
   * @param array $keys Array of keys for remove
   * @return array
   */
  public static function removeElementsByKey($array, $keys) {
    foreach ($keys as $key) {
      if (array_key_exists($key, $array)) {
        unset($array[$key]);
      }
    }

    return $array;
  }
}