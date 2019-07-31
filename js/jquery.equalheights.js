/**
 * Equal Heights Plugin
 * Equalize the heights of elements. Great for columns or any elements
 * that need to be the same size (floats, etc).
 *
 * Version 1.0
 * Updated 12/10/2008
 *
 * Copyright (c) 2008 Rob Glazebrook (cssnewbie.com)
 *
 * Usage: $(object).equalHeights([minHeight], [maxHeight]);
 *
 * Example 1: $(".cols").equalHeights(); Sets all columns to the same height.
 * Example 2: $(".cols").equalHeights(400); Sets all cols to at least 400px tall.
 * Example 3: $(".cols").equalHeights(100,300); Cols are at least 100 but no more
 * than 300 pixels tall. Elements with too much content will gain a scrollbar.
 *
 */

(function($) {
  $.fn.equalHeight = function(){
    var height = 0,
    reset = $.browser.msie ? "1%" : "auto";
    return this
    .css("min-height", reset)
    .each(function() {
      height = Math.max(height, this.offsetHeight);
    })
    .css("min-height", height)
    .each(function() {
      var h = this.offsetHeight;
      if (h > height) {
        $(this).css("min-height", height - (h - height));
      };
    });
  };
})(jQuery);

