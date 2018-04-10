<?php

/**
 * @file
 * SL7 date formats.
 *  
 * @author Semyon Dragunov <sam.dragunov@gmail.com>
 * https://github.com/SemyonDragunov
 */

define('SL7_DATE_TYPE_NO_HOUR', 'sl7_date_type_no_hour');
define('SL7_DATE_TYPE_HOUR', 'sl7_date_type_hour');
define('SL7_DATE_TYPE_WEEKDAY_NO_HOUR', 'sl7_date_type_weekday_no_hour');
define('SL7_DATE_TYPE_WEEKDAY_HOUR', 'sl7_date_type_weekday_hour');
define('SL7_DATE_FORMAT_NO_HOUR', 'j.m.Y');
define('SL7_DATE_FORMAT_HOUR', 'j.m.Y - H:i');
define('SL7_DATE_FORMAT_WEEKDAY_NO_HOUR', 'D, j.m.Y');
define('SL7_DATE_FORMAT_WEEKDAY_HOUR', 'D, j.m.Y - H:i');

/**
 * Implements hook_date_formats().
 */
function sl7_control_panel_date_formats() {
  $formats = array();

  $formats[] = array(
    'type' => SL7_DATE_TYPE_NO_HOUR,
    'format' => SL7_DATE_FORMAT_NO_HOUR,
    'locales' => array(),
  );
  $formats[] = array(
    'type' => SL7_DATE_TYPE_HOUR,
    'format' => SL7_DATE_FORMAT_HOUR,
    'locales' => array(),
  );
  $formats[] = array(
    'type' => SL7_DATE_TYPE_WEEKDAY_NO_HOUR,
    'format' => SL7_DATE_FORMAT_WEEKDAY_NO_HOUR,
    'locales' => array(),
  );
  $formats[] = array(
    'type' => SL7_DATE_TYPE_WEEKDAY_HOUR,
    'format' => SL7_DATE_FORMAT_WEEKDAY_HOUR,
    'locales' => array(),
  );

  return $formats;
}

/**
 * Implements hook_date_format_types().
 */
function sl7_control_panel_date_format_types() {
  $types = array();
  $types[SL7_DATE_TYPE_NO_HOUR] = t('Without time');
  $types[SL7_DATE_TYPE_HOUR] = t('With time');
  $types[SL7_DATE_TYPE_WEEKDAY_NO_HOUR] = t('With the day of the week, without time');
  $types[SL7_DATE_TYPE_WEEKDAY_HOUR] = t('With day of the week and time');
  return $types;
}