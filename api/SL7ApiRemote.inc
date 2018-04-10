<?php

/**
 * @file
 *  SL7 Remote API.
 * 
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

class SL7ApiRemote {
  /**
   * Send POST request and return result.
   *
   * @param string $url Url
   * @param array $params Array of params
   * @return stdClass
   */
  public static function sendPost($url, $params) {
    return drupal_http_request($url, array(
      'headers' => array('Content-Type' => 'application/x-www-form-urlencoded'),
      'method' => 'POST',
      'data' => drupal_http_build_query($params),
    ));
  }
}