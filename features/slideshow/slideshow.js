jQuery(document).ready(function($) {
	if(parseInt(Drupal.settings.slideshow.typeSlideshow)=='0') {
		if(parseInt(Drupal.settings.slideshow.show_controlNav)==2) {
			$('#carousel').flexslider({
				animation: "slide",
				controlNav: false,
				animationLoop: false,
				slideshow: false,
				itemWidth: 210,
				itemMargin: 5,
				asNavFor: '#slider'
			});
			 $('#slider').flexslider({
			 animation: Drupal.settings.slideshow.animation,              
				animation: Drupal.settings.slideshow.animation,              
				slideshow: parseInt(Drupal.settings.slideshow.autoSlideshow),
				slideshowSpeed: parseInt(Drupal.settings.slideshow.slideshowSpeed),
				animationDuration: parseInt(Drupal.settings.slideshow.animationDuration),
				directionNav: parseInt(Drupal.settings.slideshow.show_directionNav),
				pauseOnHover: parseInt(Drupal.settings.slideshow.pauseOnHover),
				controlNav: false,
				animationLoop: true,
				sync: "#carousel"
			  });
			  
		}
		else {
			$('#slider').flexslider({
				animation: Drupal.settings.slideshow.animation,              
				slideshow: parseInt(Drupal.settings.slideshow.autoSlideshow),
				slideshowSpeed: parseInt(Drupal.settings.slideshow.slideshowSpeed),
				animationDuration: parseInt(Drupal.settings.slideshow.animationDuration),
				directionNav: parseInt(Drupal.settings.slideshow.show_directionNav),
				controlNav: parseInt(Drupal.settings.slideshow.show_controlNav),
				pauseOnHover: parseInt(Drupal.settings.slideshow.pauseOnHover)
			});
		}
	}
	else if (parseInt(Drupal.settings.slideshow.typeSlideshow)==1){
		$("#zslider").zAccordion({
			timeout: parseInt(Drupal.settings.slideshow.timeOut),
			speed: parseInt(Drupal.settings.slideshow.slideSpeed),
			width:Drupal.settings.slideshow.widthWrapper,
			slideWidth: Drupal.settings.slideshow.slideWidth,
			height:Drupal.settings.slideshow.slideHeight,
			slideClass: Drupal.settings.slideshow.slideClasses,
			easing: Drupal.settings.slideshow.slideEasing,
			pause: parseInt(Drupal.settings.slideshow.slidePause),
			trigger: Drupal.settings.slideshow.slideTrigger,
			auto: parseInt(Drupal.settings.slideshow.slideAuto)
		});
	}
});