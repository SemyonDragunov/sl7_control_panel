<?php

/**
 * @file
 * Patterns.
 */

/**
 * Singleton.
 */
trait SL7PatternSingleton
{
  protected static $instance;

  final public static function getInstance()
  {
    return isset(static::$instance)
      ? static::$instance
      : static::$instance = new static;
  }

  /**
   * For override at class.
   */
  protected function init() {}

  final private function __construct() {
    $this->init();
  }
  final private function __wakeup() {}
  final private function __clone() {}
}