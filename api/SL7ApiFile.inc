<?php

/**
 * @file
 *  SL7 File API.
 *  
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

class SL7ApiFile {

  /**
   * Set permanent status to file in drupal system.
   *
   * @param $file
   *  Object or FID.
   * @param string $module
   *  The name of module for save file.
   * @param string $type
   *  Type of file.
   * @param string $id
   *  ID of Type.
   *
   * @return stdClass File.
   */
  public static function setPermanent($file, $module, $type, $id) {
    $file = is_object($file) ? $file : file_load($file);

    if ($file->status == 0) {
      $file->status = FILE_STATUS_PERMANENT;
      file_save($file);
      file_usage_add($file, $module, $type, $id);
    }

    return $file;
  }
}