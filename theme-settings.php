<?php
/**
 * Implements hook_form_system_theme_settings_alter().
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form.
 */
 include_once('features/slideshow/logics.inc');
//Get patterns Background
function zframe_get_backgrounds() {
  $theme_name = 'zframe';
  $path_to_theme = drupal_get_path('theme', $theme_name);
  $images = file_scan_directory($path_to_theme.'/images/patterns', '/^.*\.(png|jpg|jpge|gif)$/');
  return $images;
}
//Get images background form upload
function zframe_get_backgrounds_bg() {
  $path_to_files =  file_stream_wrapper_get_instance_by_uri('public://')->getDirectoryPath();
  $images_bg = file_scan_directory($path_to_files.'/bg/thumb', '/^.*\.(png|jpg|jpge|gif)$/'); 
  return $images_bg;
}

function zframe_form_system_theme_settings_alter(&$form, &$form_state, $form_id = NULL)  {
  global $base_url;

  // Work-around for a core bug affecting admin themes. See issue #943212.
  
  $current_theme_path = drupal_get_path('theme', 'zframe');
  // Load zframe Features
  foreach (file_scan_directory($current_theme_path . '/features', '/settings.inc/') as $file) {
    require($file->uri);
  }
  
  if (isset($form_id)) {
    return;
  };
  $form['layout_your_theme'] = array(
    '#type' => 'fieldset',
    '#title' => t('Layout options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  if ($form['var']['#value'] == 'theme_zframe_settings') {
    $form['layout_your_theme']['layouts'] = array(
      '#type'          => 'radios',
      '#options'       => array(
        'three-col-grail' => t('Sidebar - Content - Sidebar'),
        'three-col-right' => t('Content - Sidebar - Sidebar'),
		    'three-col-left' => t('Sidebar - Sidebar - Content') ,
      ),
      '#default_value' => theme_get_setting('layouts'),
    );
  }
  
  // Load Features

  // Create the form using Forms API: http://api.drupal.org/api/7

  /* -- Delete this line if you want to use this setting
  $form['zframe_example'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('zframe sample setting'),
    '#default_value' => theme_get_setting('zframe_example'),
    '#description'   => t("This option doesn't do anything; it's just an example."),
  );
  // */

  // Remove some of the base theme's settings.
  /* -- Delete this line if you want to turn off this setting.
  unset($form['themedev']['zen_wireframes']); // We don't need to toggle wireframes on this site.
  // */

  // We are editing the $form in place, so we don't need to return anything.
  
   // Skin settings
  $form['at']['skins'] = array(
    '#type' => 'fieldset',
    '#title' => t('Skin options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
 $form['at']['skins']['skins_type'] = array(
  '#type' => 'radios',
  '#title' => t('Please select a skin'),
  '#default_value' => (theme_get_setting('skins_type')?theme_get_setting('skins_type'):'default'),
  '#options' => array(
      'default' => t('Default')
    ),
  );
  
   // Background settings
  $arrImages = array('none'=>t('None'));
  foreach(zframe_get_backgrounds() as $bg) {
    $variables = array(
      'path' => $bg->uri,
      'alt' => $bg->name,
      'title' => $bg->name,
      'width' => '25px',
      'height' => '25px',
      'attributes' => array('class' => 'bg-img'),
    );
    $img = theme('image', $variables);
    $arrImages[$base_url.'/'.$bg->uri] = $img; 
  };
  $form['background_setting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Background Configuration'),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['background_setting']['bgs'] = array(
    '#type' => 'fieldset',
    '#title' => t('Background Patterns (repeated)'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );    
  //upload your Patterns
  $form['background_setting']['bgs']['upload_pattern'] = array(
    '#type' => 'file',
    '#title' => t('Upload a new pattern'),
    '#weight' => 1,
  );
  $form['background_setting']['bgs']['bgs_pattern'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select Background Pattern'),
    '#weight' => 2,
  );
  $form['background_setting']['bgs']['bgs_pattern']['bgs_type'] = array(
    '#type' => 'radios',
    '#default_value' => (theme_get_setting('bgs_type')?theme_get_setting('bgs_type'):'none'),
    '#options' => $arrImages,
    '#weight' => 1,
  );
  //Upload custom Background
  $form['background_setting']['your_background'] = array(
    '#type' => 'fieldset',
    '#title' => t('Background Images (No-repeated)'),
    '#description'   => t("If background image is selected it replaces the above patterns."),
    '#weight' => 1,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );  
  //upload
  $form['background_setting']['your_background']['upload_bg'] = array(
    '#type' => 'file',
    '#title' => t('Upload a new background'),
    '#weight' => 1,
  );
  //danh sach background da upload
  $arrImages_bg = array('none'=>t('None'));
  foreach(zframe_get_backgrounds_bg() as $bg_image_temp) {
    $variables_bg = array(
      'path' => $bg_image_temp->uri,
      'alt' => $bg_image_temp->name,
      'title' => $bg_image_temp->name,
      'width' => '150px',
      'height' => '100px',
      'attributes' => array('class' => 'bg-image'),
    );
    $bg_image = theme('image', $variables_bg);
    $arrImages_bg[$base_url.'/'.$bg_image_temp->uri] = $bg_image; 
  };
  $form['background_setting']['your_background']['bgs_img'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select Background Image'),
    '#weight' => 2,
  );
  $form['background_setting']['your_background']['bgs_img']['bgs_img_type'] = array(
    '#type' => 'radios',
    '#default_value' => (theme_get_setting('bgs_img_type')?theme_get_setting('bgs_img_type'):'none'),
    '#options' => $arrImages_bg,
  );
  //Custom position
  $form['background_setting']['your_background']['position_choose'] = array(
    '#type' => 'select',
    '#title' => t('Select background position'),
    '#weight' => 3,
    '#options'=> array (
      'top left' => t('Top Left'),
      'top center' => t('Top Center'),
      'top right' => t('Top Right'),
      'center center' => t('Center Center'),
      'bottom left' => t('Bottom Left'),
      'bottom center' => t('Bottom Center'),
      'bottom right' => t('Bottom Right'),
    ),
    '#default_value' => theme_get_setting('position_choose'),
  );
  //Repeat or no-repeat
  /*
  $form['background_setting']['your_background']['bg_repeat'] = array(
    '#type' => 'checkbox',
    '#title' => t('Repeat'),
    '#weight' => 4,
    '#default_value' => theme_get_setting('bg_repeat'),
  );
  */
  //delete background images
  /*
  $form['background_setting']['your_background']['bg_delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete this background.'),
      '#weight' => 5,
      '#default_value' => FALSE,
    );*/

  $form['theme_settings']['#collapsible'] = TRUE;
  $form['theme_settings']['#collapsed'] = TRUE;
  $form['logo']['#collapsible'] = TRUE;
  $form['logo']['#collapsed'] = TRUE;
  $form['favicon']['#collapsible'] = TRUE;
  $form['favicon']['#collapsed'] = TRUE;
   
  $form['theme_settings']['#weight'] = 1;
  $form['logo']['#weight'] = 2;
  $form['favicon']['#weight'] = 3;
}