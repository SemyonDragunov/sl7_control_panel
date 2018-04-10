<?php

/**
 * @file
 * SL7 API Debug.
 * 
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

/**
 * For debug other classes.
 */
trait SL7Debug
{
  public $debug_error_msg = array();

  final public function newError($msg) {
    $this->debug_error_msg[] = $msg;
  }

  final public function hasError() {
    if (!empty($this->debug_error_msg)) {
      return TRUE;
    }
    return FALSE;
  }

  final public function getError() {
    return $this->debug_error_msg;
  }
}