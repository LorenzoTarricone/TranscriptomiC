#include "mainwindow.h"

arrow::Status RunMain() {
    // Builders are the main way to create Arrays in Arrow from existing values that are not
     // on-disk. In this case, we'll make a simple array, and feed that in.
     // Data types are important as ever, and there is a Builder for each compatible type;
     // in this case, int8.
     arrow::Int8Builder int8builder;
     int8_t days_raw[5] = {1, 12, 17, 23, 28};
     // AppendValues, as called, puts 5 values from days_raw into our Builder object.
     ARROW_RETURN_NOT_OK(int8builder.AppendValues(days_raw, 5));

     // We only have a Builder though, not an Array -- the following code pushes out the
     // built up data into a proper Array.
     std::shared_ptr<arrow::Array> days;
     ARROW_ASSIGN_OR_RAISE(days, int8builder.Finish());

     // Builders clear their state every time they fill an Array, so if the type is the same,
      // we can re-use the builder. We do that here for month values.
      int8_t months_raw[5] = {1, 3, 5, 7, 1};
      ARROW_RETURN_NOT_OK(int8builder.AppendValues(months_raw, 5));
      std::shared_ptr<arrow::Array> months;
      ARROW_ASSIGN_OR_RAISE(months, int8builder.Finish());

      // Now that we change to int16, we use the Builder for that data type instead.
       arrow::Int16Builder int16builder;
       int16_t years_raw[5] = {1990, 2000, 1995, 2000, 1995};
       ARROW_RETURN_NOT_OK(int16builder.AppendValues(years_raw, 5));
       std::shared_ptr<arrow::Array> years;
       ARROW_ASSIGN_OR_RAISE(years, int16builder.Finish());

}


