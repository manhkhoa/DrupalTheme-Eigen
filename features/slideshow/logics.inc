<?php // $Id$
/**
 * Generate markup for eigen's slides.
 *
 * @return <string>
 *    HTML markup to printo into page
 */
function eigen_slides_markup($slides) {
  if ($slides && theme_get_setting('slide_usage') != 0) {
    // Add javascript to manage slides
    eigen_slides_add_js(count($slides));

    // Generate HTML markup for slides
    return eigen_slide_markup($slides);
  } else {
    return '';
  }
}

/**
 * Add JS required to manage slide into this page.
 *
 * @param <int> $num_slides
 *    Number of slide visible into this page
 */
function eigen_slides_add_js($num_slides) {
  // add the required javascript
  
	if(theme_get_setting('type_slideshow')==0){
		// Flexslider
		drupal_add_js(
		  array(
			'slideshow' => array(
			  'typeSlideshow' =>theme_get_setting('type_slideshow'),
			  'autoSlideshow' => theme_get_setting('autoSlideshow'),
			  'animation' => theme_get_setting('animation')?theme_get_setting('animation'):'fade',
			  'show_controlNav' => theme_get_setting('show_controlNav'),  
			  'show_directionNav' => theme_get_setting('show_directionNav'),
			  'slideshowSpeed' => theme_get_setting('slideshowSpeed')?theme_get_setting('slideshowSpeed'):7000,
			  'animationDuration' => theme_get_setting('animationDuration')?theme_get_setting('animationDuration'):600,
			  'pauseOnHover' => theme_get_setting('pauseOnHover'),
			)
		  ),
		  array('type' => 'setting')
		);
	}
	else if(theme_get_setting('type_slideshow')==1) {
		// Zaccordion
		drupal_add_js(
		  array(
			'slideshow' => array(
			  'typeSlideshow' =>theme_get_setting('type_slideshow'),
			  'timeOut' => theme_get_setting('time_out'),
			  'slideSpeed' => theme_get_setting('slide_speed'),  
			  'widthWrapper' => theme_get_setting('width_wrapper_slide'),
			  'slideWidth' => theme_get_setting('slide_width'),  
			  'tabWidth' => theme_get_setting('tab_width'),
			  'slideHeight' => theme_get_setting('slide_height'),
			  'slideClasses' => theme_get_setting('slide_classes'),
			  'slideAuto' => theme_get_setting('slide_auto'),   
			  'slideTrigger' => theme_get_setting('slide_trigger'),
			  'slidePause' => theme_get_setting('slide_pause'),
			  'slideEasing' => theme_get_setting('slide_easing'),
			)
		  ),
		  array('type' => 'setting')
		);
	}
    drupal_add_js(path_to_theme() . '/features/slideshow/slideshow.js');
}

/**
 * Generate slides markup.
 *
 * @return <string>
 *    HTML code to display slide markup.
 */
function eigen_slide_markup($slides) {
	if(theme_get_setting('type_slideshow')==0){
	  $output ='<div id="slider" class="flexslider">';
	  $output .= '<ul class="slides">';
	  
	  foreach($slides as $i => $slide) {
		$variables = array(
		  'path'  => $slide['image_path'],
		  'alt' => t('@image_desc', array('@image_desc'=>$slide['image_description'])),
		  'title'   => t('@image_title', array('@image_title'=>$slide['image_title'])),
		  'attributes' => array(
			'class' => 'slide' . ($i != 0 ? ' eigen-hide-no-js' : ''), // hide all the slides except #1
			'id' => 'slide-number-' . $i,
			'longdesc' => t('@image_desc', array('@image_desc'=>$slide['image_description']))
		  ),
		);
		// Draw image
		$image   = theme('image', $variables);
		// Remove link if is the same page
		$slide['image_url'] = ($slide['image_url'] == current_path()) ? FALSE  : $slide['image_url'];

		// Add link (if required)
		$output .= '<li>';
		$output .= $slide['image_url'] ? l($image, $slide['image_url'], array('html' => TRUE)) : $image;
		if(theme_get_setting('slide_showtext')) {
		  $output .= '<div class="title-desc-container"><p class="slide-title">'.($slide['image_url'] ? l($slide['image_title'], $slide['image_url'], array('html' => TRUE)) : $slide['image_title']).'</p><p class="slide-desc">'.$slide['image_description'].'</p></div>';
		}
		$output .= '</li>';
	  }
	  $output .= '</ul>';
	  $output .='</div>';
	  if(theme_get_setting('show_controlNav')==2){
	  $output .='<div id="carousel" class="flexslider">';
		  $output .='<ul class="slides">';
			  foreach($slides as $i => $slide) {
				$variables = array(
				  'path'  => $slide['image_path'],
				  'alt' => t('@image_desc', array('@image_desc'=>$slide['image_description'])),
				  'title'   => t('@image_title', array('@image_title'=>$slide['image_title'])),
				  'attributes' => array(
					'class' => 'slide' . ($i != 0 ? ' eigen-hide-no-js' : ''), // hide all the slides except #1
					'id' => 'slide-number-' . $i,
					'longdesc' => t('@image_desc', array('@image_desc'=>$slide['image_description']))
				  ),
				);
					// Draw image
				  $image   = theme('image', $variables);
				  $output .='<li>'.$image.'</li>';
				}	
		  $output .='</ul>';
	  $output .='</div>';
	  }
	}
	else if(theme_get_setting('type_slideshow')==1){
		$output ='<ul id="zslider" class="zslider">';
			foreach($slides as $i => $slide) {
				$variables = array(
				  'path'  => $slide['image_path'],
				  'alt' => t('@image_desc', array('@image_desc'=>$slide['image_description'])),
				  'title'   => t('@image_title', array('@image_title'=>$slide['image_title'])),
				  'attributes' => array(
					'class' => 'slide' . ($i != 0 ? ' eigen-hide-no-js' : ''), // hide all the slides except #1
					'id' => 'slide-number-' . $i,
					'longdesc' => t('@image_desc', array('@image_desc'=>$slide['image_description']))
				  ),
				);
				// Draw image
				$image   = theme('image', $variables);
				// Remove link if is the same page
				$slide['image_url'] = ($slide['image_url'] == current_path()) ? FALSE  : $slide['image_url'];

				// Add link (if required)
				$output .= '<li>';
				$output .= $image;
				if(theme_get_setting('slide_showtext')) {
				  $output .= '<div class="slider-bg"></div>';
				  $output .= '<div class="slide-info"><p class="slide-title">'.($slide['image_url'] ? l($slide['image_title'], $slide['image_url'], array('html' => TRUE)) : $slide['image_title']).'</p><p class="slide-desc">'.$slide['image_description'].'</p></div>';
				}
			$output .= '</li>';
			}
	  $output .= '</ul>';
	}	
	  
	  return $output;
}

/**
 * Get slide to show into current page in accord with settings
 *
 * @return <array>
 *    slides to show
 */
function eigen_show_slides() {
  $slides = eigen_get_slides(FALSE);
  $display_slides = array();

  // Current path alias
  $path = drupal_strtolower(drupal_get_path_alias($_GET['q']));

  // Check visibility for each slide
  foreach ($slides as $slide) {
    // Pages
    $pages = drupal_strtolower($slide['image_visibility']);

    // Check path for alias, and (if required) for path
    $page_match = drupal_match_path($path, $pages);
    if ($path != $_GET['q']) {
      $page_match = $page_match || drupal_match_path($_GET['q'], $pages);
    }

    // Add slide to visible slide
    if ($page_match) {
      $display_slides[] = $slide;
    }
  }
  return $display_slides;
}

/**
 * Get slide settings.
 *
 * @param <bool> $all
 *    Return all slides or only active.
 *
 * @return <array>
 *    Settings information
 */
function eigen_get_slides($all = TRUE) {
  // Get all slides
  $slides = variable_get('theme_eigen_slide_settings', array());
  // Create list of slide to return
  $slides_value = array();
  foreach ($slides as $slide) {
    if ($all || $slide['image_published']) {
      // Add weight param to use `drupal_sort_weight`
      $slide['weight'] = $slide['image_weight'];
      $slides_value[] = $slide;
    }
  }

  // Sort image by weight
  usort($slides_value, 'drupal_sort_weight');

  return $slides_value;
}

/**
 * Set slide settings.
 *
 * @param <array> $value
 *    Settings to save
 */
function eigen_set_slides($value) {
  variable_set('theme_eigen_slide_settings', $value);
}

/**
 * Save settings data.
 */
function eigen_settings_submit($form, &$form_state) {
  $settings = array();
/*
  //Xoa anh background
   if ($image['image_delete']) {
      // Delete slide file
      file_unmanaged_delete($image['image_path']);
      // Delete slide thumbnail file
      file_unmanaged_delete($image['image_thumb']);
    }
  //Xoa anh background
*/
  // Update image field
  foreach ($form_state['input']['images'] as $image) {
    if (is_array($image)) {
      $image = $image['image'];
      
      if ($image['image_delete']) {
        // Delete slide file
        file_unmanaged_delete($image['image_path']);
        // Delete slide thumbnail file
        file_unmanaged_delete($image['image_thumb']);
      } else {
        // Update image
        $settings[] = $image;
      }
    }
  }
  
  // Check for a new uploaded file, and use that if available.
  if ($file = file_save_upload('image_upload')) {
    $file->status = FILE_STATUS_PERMANENT;
    if ($image = eigen_save_image($file)) {
      // Put new image into settings
      $settings[] = $image;
    }
  }

  if ($file = file_save_upload('upload_bg')) {
    if ($image = eigen_save_image_bg($file)) {
      // Put new image into settings
      //$settings[] = $image;
    }
  }
  if ($file = file_save_upload('upload_pattern')) {
    if ($image = eigen_save_pattern_bg($file)) {
      // Put new image into settings
      //$settings[] = $image;
    }
  }

  // Save settings
  eigen_set_slides($settings);
}

/**
 * Check if folder is available or create it.
 *
 * @param <string> $dir
 *    Folder to check
 */
function eigen_check_dir($dir) {
  // Normalize directory name
  $dir = file_stream_wrapper_uri_normalize($dir);

  // Create directory (if not exist)
  file_prepare_directory($dir,  FILE_CREATE_DIRECTORY);
}
/**
 * Save file uploaded by user and generate setting to save.
 *
 * @param <file> $file
 *    File uploaded from user
 *
 * @param <string> $slide_folder
 *    Folder where save image
 *
 * @param <string> $slide_thumb_folder
 *    Folder where save image thumbnail
 *
 * @return <array>
 *    Array with file data.
 *    FALSE on error.
 */
function eigen_save_image($file, $slide_folder = 'public://slide/', $slide_thumb_folder = 'public://slide/thumb/') {
  // Check directory and create it (if not exist)
  eigen_check_dir($slide_folder);
  eigen_check_dir($slide_thumb_folder);

  $parts = pathinfo($file->filename);
  $destination = $slide_folder . $parts['basename'];
  $setting = array();

  $file->status = FILE_STATUS_PERMANENT;
  
  // Copy temporary image into slide folder
  if ($img = file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
    // Generate image thumb
    $image = image_load($destination);
    $small_img = image_scale($image, 300, 100);
    $image->source = $slide_thumb_folder . $parts['basename'];
    image_save($image);

    // Set image info
    $setting['image_path'] = $destination;
    $setting['image_thumb'] = $image->source;
    $setting['image_title'] = '';
    $setting['image_description'] = '';
    $setting['image_url'] = '<front>';
    $setting['image_weight'] = 0;
    $setting['image_published'] = FALSE;
    $setting['image_visibility'] = '*';
	

    return $setting;
  }
  
  return FALSE;
}
//function save images background
function eigen_save_image_bg($file, $bg_folder = 'public://bg/', $bg_thumb_folder = 'public://bg/thumb/') {
  // Check directory and create it (if not exist)
  eigen_check_dir($bg_folder);
  eigen_check_dir($bg_thumb_folder);

  $parts = pathinfo($file->filename);
  $destination = $bg_folder . $parts['basename'];
  $setting_bg = array();

  $file->status = FILE_STATUS_PERMANENT;
  
  // Copy temporary image into slide folder
  if ($img = file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
    // Generate image thumb
    $image = image_load($destination);
    $small_img = image_scale($image, 300, 100);
    $image->source = $bg_thumb_folder . $parts['basename'];
    image_save($image);

    // Set image info
    $setting_bg['bg_image_path'] = $destination;
    $setting_bg['bg_image_thumb'] = $image->source;
    $setting_bg['bg_image_title'] = '';
    $setting_bg['bg_image_description'] = '';
    $setting_bg['bg_image_url'] = '<front>';
    $setting_bg['bg_image_weight'] = 0;
    $setting_bg['bg_image_published'] = FALSE;
    $setting_bg['bg_image_visibility'] = '*';  

    return $setting_bg;
  }
  
  return FALSE;
}

//function save images background
function eigen_save_pattern_bg($file, $pattern_folder = 'public://bg/pattern/', $pattern_thumb_folder = 'public://bg/pattern/thumb/') {
  // Check directory and create it (if not exist)
  $current_theme_path = drupal_get_path('theme', 'eigen');
  $pattern_thumb_folder = $current_theme_path.'/images/patterns/';
  eigen_check_dir($pattern_folder);
  eigen_check_dir($pattern_thumb_folder);

  $parts = pathinfo($file->filename);
  $destination = $pattern_folder . $parts['basename'];
  $setting_pattern = array();

  $file->status = FILE_STATUS_PERMANENT;
  
  // Copy temporary image into slide folder

  if ($img = file_copy($file, $destination, FILE_EXISTS_REPLACE)) {
    //path to theme
    
    // Generate image thumb
    
    $image = image_load($destination);
    //$small_img = image_scale($image, 300, 100);
    $image->source = $pattern_thumb_folder . $parts['basename'];
    image_save($image);

    // Set image info
    $setting_pattern['bg_image_path'] = $destination;
    $setting_pattern['bg_image_thumb'] = $image->source;
    $setting_pattern['bg_image_title'] = '';
    $setting_pattern['bg_image_description'] = '';
    $setting_pattern['bg_image_url'] = '<front>';
    $setting_pattern['bg_image_weight'] = 0;
    $setting_pattern['bg_image_published'] = FALSE;
    $setting_pattern['bg_image_visibility'] = '*';  

    return $setting_pattern;
  }

  
  return FALSE;
}


/**
 * Provvide default installation settings for eigen.
 */
function eigen_install() {
  // Deafault data
  $file = new stdClass;
  $slides = array();
  // Source base for images
  $src_base_path = drupal_get_path('theme', 'eigen');
  $default_slides = theme_get_setting('default_slides');
  
  // Put all image as slides
  foreach ($default_slides as $i => $data) {
    $file->uri = $src_base_path . '/' . $data['image_path'];
    $file->filename = $file->uri;

    $slide = eigen_save_image($file);
    unset($data['image_path']);
    $slide = array_merge($slide, $data);
    $slides[$i] = $slide;
  }
  
  // Save slide data
  eigen_set_slides($slides);
  
  // Flag theme is installed
  variable_set('theme_eigen_first_install', FALSE);
}

/**
 * Generate form to mange slide informations
 *
 * @param <array> $image_data
 *    Array with image data
 *
 * @return <array>
 *    Form to manage image informations
 */
function eigen_slide_form($image_data) {
    $img_form = array();

    // Image preview
    $img_form['image_preview'] = array(
      '#markup' => theme('image', array('path' => $image_data['image_thumb'])),
    );

    // Image path
    $img_form['image_path'] = array(
      '#type' => 'hidden',
      '#value' => $image_data['image_path'],
    );

    // Thumbnail path
    $img_form['image_thumb'] = array(
      '#type' => 'hidden',
      '#value' => $image_data['image_thumb'],
    );

    // Image title
    $img_form['image_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => $image_data['image_title'],
    );

    // Image description
    $img_form['image_description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => $image_data['image_description'],
    );

    // Url
    $img_form['image_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Url'),
      '#default_value' => $image_data['image_url'],
    );
    // Image visibility
    $img_form['image_visibility'] = array(
      '#type' => 'textarea',
      '#title' => t('Visibility'),
      '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
      '#default_value' => $image_data['image_visibility'],
    );

    // Image weight
    $img_form['image_weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $image_data['image_weight'],
    );

    // Image is published
    $img_form['image_published'] = array(
      '#type' => 'checkbox',
      '#title' => t('Published'),
      '#default_value' => $image_data['image_published'],
    );

    // Delete image
    $img_form['image_delete'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete image.'),
      '#default_value' => FALSE,
    );

    return $img_form;
}
