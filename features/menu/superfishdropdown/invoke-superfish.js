(function ($) {
	
	$(document).ready(function() {
		$('#menu-bar ul.menu').Gpsuperfish({
				GpsuperfishWidth: Drupal.settings.menu.submenu_width,
				delay:     parseInt(Drupal.settings.menu.menu_delay),
				animationShow:   Drupal.settings.menu.animationShow,
				speedShow:       parseInt(Drupal.settings.menu.menu_speed_show),
				easingShow: Drupal.settings.menu.menu_easing_show,
				animationHide:   Drupal.settings.menu.animationHide,
				speedHide:     parseInt(Drupal.settings.menu.menu_speed_hide),
				easingHide:    Drupal.settings.menu.menu_easing_hide,
				autoArrows:  true,
				dropShadows: true 
		});
      
	});
}(jQuery));